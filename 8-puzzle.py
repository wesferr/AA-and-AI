#/usr/bin/python3
# -*- coding: utf-8 -*-

import numpy as np
from heap import *
from copy import deepcopy

class State(object):
	def __init__(self, state = [], depth = 0, move = ''):
		self.depth = depth
		self.moves = move
		self.state = state

	def up(self):
	  nstate = self.state[:]
	  a = nstate.index(0)
	  b = a-3
	  if(b >= 0):
	  	nstate[a], nstate[b] = nstate[b], nstate[a]
	  return State(nstate, self.depth+1, self.moves + 'u')

	def down(self):
	  nstate = self.state[:]
	  a = nstate.index(0)
	  b = a+3
	  if(b <= 8):
	  	nstate[a], nstate[b] = nstate[b], nstate[a]
	  return State(nstate, self.depth+1, self.moves + 'd')

	def left(self):
	  nstate = self.state[:]
	  a = nstate.index(0)
	  b = a+1
	  if(b%3 > 0):
	  	nstate[a], nstate[b] = nstate[b], nstate[a]
	  return State(nstate, self.depth+1, self.moves + 'l')

	def right(self):
		nstate = self.state[:]
		a = nstate.index(0)
		b = a+1
		if( a < 8 and (b%3) < 2):
			nstate[a], nstate[b] = nstate[b], nstate[a]
		return State(nstate, self.depth+1, self.moves + 'r')

class _8puzzle(object):
	def __init__(self):
		self.goal  = State( [0,1,2,3,4,5,6,7,8] )
		self.start = State( [8,6,4,2,1,0,3,5,7] )
			
		 
	def astar(self):
	
		def heur1(x):
			a = 0
			for i,j in zip(x,self.goal.state):
				if( j != i ):
					a+=1
			return a
				
		visitados={}
		heap=[]
		heappush( heap, (heur1(self.start.state), self.start) )
		atual = heap[0][1]
		if(atual.state == self.goal.state):
			return atual
		while(len(heap)):
			visitados[str(atual.state)]=True
			sucessors = [atual.up(), atual.down(), atual.left(), atual.right()]
			for i in sucessors:
				if(i.state == self.goal.state):
					return i
				if(str(i.state) not in visitados):
					heappush( heap, (heur1(i.state), i ) )
			atual = heappop(heap)[1]

def main():
	a = _8puzzle()
	astar = a.astar()
	print("8-Puzzle heuristica peças fora do lugar\nProfundidade da solução: {}\nMovimentos(u,d,l,r): {}".format(astar.depth, astar.moves))

if __name__ == "__main__":
	main()
