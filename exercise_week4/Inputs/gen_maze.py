from __future__ import print_function
from random import shuffle, randrange

def make_maze(w = 42, h = 43):
	print( h*2 +1, w*2 + 1)
	vis = [[0] * w + [1] for _ in range(h)] + [[1] * (w + 1)]
	ver = [["10"] * w + ['1'] for _ in range(h)] + [[]]
	hor = [['0'] + ["11"] * w  for _ in range(1)]
	hor += [["11"] * w + ['1'] for _ in range(h-1)]
	hor += [["11"] * w + ['0'] for _ in range(1)]
	def walk(x, y):
		vis[y][x] = 1

		d = [(x - 1, y), (x, y + 1), (x + 1, y), (x, y - 1)]
		shuffle(d)
		for (xx, yy) in d:
			if vis[yy][xx]: continue
			if xx == x: hor[max(y, yy)][x] = "10"
			if yy == y: ver[y][max(x, xx)] = "00"
			walk(xx, yy)

	walk(randrange(w), randrange(h))

	s = ""
	for (a, b) in zip(hor, ver):
		s += ''.join(a + ['\n'] + b + ['\n'])
	return s

if __name__ == '__main__':
	print(make_maze())
