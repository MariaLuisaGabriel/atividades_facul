import cmath
import numpy as np
import math
import matplotlib.pyplot as plt
import time

def FFT(xn):
	N = len(xn)
	if N==1:
		return xn
	else:

		Z = np.exp(-2j * np.pi * np.arange(N)/ N)
		par = FFT(xn[::2])
		impar = FFT(xn[1::2])

		Aeven = par+Z[:int(N/2)]*impar
		Aodd = par+Z[int(N/2):]*impar
		
		return np.concatenate([Aeven,Aodd])

def DFT(lista):
    n = len(lista)
    result = []
    Z = cmath.exp(-2 * cmath.pi * 1j / n) #J e a unidade imaginaria
    for k in range(n):
        soma = 0
        for t in range(n):
            soma += lista[t] * Z ** (t * k)
        result.append(soma)
    return result

def calcular_freq_domainDFT(sinal):
    dft_sinal = DFT(sinal)
    magnitudes = np.abs(dft_sinal) #magnitude = valor absoluto do numero complexo
    T = len(sinal)
    frequencias = [i * 1/T for i in range(T)] #frequencia para um dado ponto i e i/T onde T e o tamanho do sinal. Isso vem da definicao de frequencia que e 1/T
    magnitudes = magnitudes[:T//2] #magnitude e frequencia sao simetricas (pq complexos tem conjugados) entao pegamos so a metade
    frequencias = frequencias[:T//2]
    return frequencias, magnitudes

def calcular_freq_domainFFT(sinal):
    fft_sinal = FFT(sinal)
    magnitudes = np.abs(fft_sinal) #magnitude = valor absoluto do numero complexo
    T = len(sinal)
    frequencias = [i * 1/T for i in range(T)] #frequencia para um dado ponto i e i/T onde T e o tamanho do sinal. Isso vem da definicao de frequencia que e 1/T
    magnitudes = magnitudes[:T//2] #magnitude e frequencia sao simetricas (pq complexos tem conjugados) entao pegamos so a metade
    frequencias = frequencias[:T//2]
    return frequencias, magnitudes

verde = np.linspace(530, 600, 2**15)
verde = np.sin(verde)

#print("FFT: "+str(FFT(lista)))
#print("\n")
#print("DFT: "+str(DFT(lista)))

start = time.time()
frequencias, magnitudes = calcular_freq_domainDFT(verde)
end = time.time()
print("DFT: "+end-start)

plt.plot(frequencias, magnitudes,'g', label='verde')

start = time.time()
frequencias, magnitudes = calcular_freq_domainFFT(verde)
end = time.time()
print("FFT: "+end-start)

plt.plot(frequencias, magnitudes,'b', label='verde')

plt.title("Frequency map")
plt.show()