import numpy as np
import matplotlib.pyplot as plt
try:	
	data=np.loadtxt ("1Newton.txt")
	plt.plot(data[:,0], data[:,1])
	data=np.loadtxt ("Tochki2.txt")
	plt.plot(data[:,0], data[:,1], 'g.')
	plt.gcf().canvas.set_window_title("Polinom1 Nyutona")
	plt.minorticks_on()
	plt.grid(color="purple", which="major", linewidth=1)
	plt.grid(color="purple", which="minor", linestyle=":", linewidth=0.5)
	plt.show()
except BaseException:
	print("Net faila")
