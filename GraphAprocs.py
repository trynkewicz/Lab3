import numpy as np
import matplotlib.pyplot as plt
try:	
	data=np.loadtxt ("pol.txt")
	plt.plot(data[:,0], data[:,1])
	data=np.loadtxt ("Tochki4.txt")
	plt.plot(data[:,0], data[:,1], 'g.')
	plt.gcf().canvas.set_window_title("Aprocsimaciya")
	plt.minorticks_on()
	plt.grid(color="pink", which="major", linewidth=0.5)
	plt.grid(color="pink", which="minor", linestyle=":", linewidth=0.5)
	plt.show()
except BaseException:
	print("Net faila")
