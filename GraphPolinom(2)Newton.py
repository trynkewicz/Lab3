import numpy as np
import matplotlib.pyplot as plt
try:	
	data=np.loadtxt ("2Newton.txt")
	plt.plot(data[:,0], data[:,1])
	data=np.loadtxt ("Tochki3.txt")
	plt.plot(data[:,0], data[:,1], 'g.')
	plt.gcf().canvas.set_window_title("Polinom2 Nyutona")
	plt.minorticks_on()
	plt.grid(color="red", which="major", linewidth=1)
	plt.grid(color="red", which="minor", linestyle=":", linewidth=0.5)
	plt.show()
except BaseException:
	print("Net faila")
