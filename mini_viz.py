import matplotlib.pyplot as plt
from matplotlib.path import Path
import matplotlib.patches as patches
import json
import sys
import os



def from_json(fpath: str):
	with open(fpath, 'rb') as f:
		data = json.load(f)
	return data


def get_polygon_patch(point_vector, facecolor='grey', edgecolor=None):
	point_vector = [(p["x"], p["y"]) for p in point_vector]
	codes = [Path.MOVETO]
	codes += [Path.LINETO for _ in point_vector]
	point_vector = point_vector + [point_vector[0]]
	path = Path(point_vector, codes)
	patch = patches.PathPatch(path, lw=1, facecolor=facecolor, edgecolor=edgecolor)
	return patch


if __name__ == '__main__':

	fpath  = sys.argv[1]
	data   = from_json(fpath)
	points = data['points']
	first  = points[0]

	fig = plt.figure(figsize=(12, 6))
	ax  = fig.add_subplot(111)
	
	patch = get_polygon_patch(points)
	ax.add_patch(patch)

	plt.scatter(
		x =[p['x'] for p in points[1:]], 
		y =[p['y'] for p in points[1:]], 
		lw=5, 
		c='blue'
	)
	plt.scatter(x=first['x'], y=first['y'], lw=5, c='red')

	#plt.show()

	fout = fpath.rstrip('.json') + ".png"
	plt.savefig(fout, dpi=120)

	plt.close()





