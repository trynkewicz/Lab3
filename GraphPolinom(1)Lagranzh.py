import numpy as np
import matplotlib.pyplot as plt
try:	
	
	data=np.loadtxt ("Lagr.txt")
	plt.plot(data[:,0], data[:,1])
	data=np.loadtxt ("Tochki.txt")
	plt.plot(data[:,0], data[:,1], 'g.')
	plt.gcf().canvas.set_window_title("Polinom1 Lagranzha")
	plt.minorticks_on()
	plt.grid(color="green", which="major", linewidth=0.5)
	plt.grid(color="green", which="minor", linestyle=":", linewidth=0.5)
	plt.show()
except BaseException:
	print("Net faila")
