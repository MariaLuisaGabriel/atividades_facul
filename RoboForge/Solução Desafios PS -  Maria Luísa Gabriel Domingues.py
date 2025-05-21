import math
import random
import numpy

#Nivel 0=================================================================================

def FizzBuzz(i):
    #por definição, quando um número é divisível por a e b, ele também é divisível por a*b (preguiça de fazer and)
    if i%15==0:
        return "FizzBuzz"
    elif i%5==0:
        return "Buzz"
    elif i%3==0:
        return "Fizz"
    else:
        return "#"

#print(str(FizzBuzz(90)))
#print(str(FizzBuzz(20)))
#print(str(FizzBuzz(18)))
#print(str(FizzBuzz(7)))

#Nivel 1===================================================================================

def geraListaPrimos(limite):
    listaPrimos = []

    for i in range(1,limite):
        flag = True
        for j in listaPrimos:
            if i%j==0 and j!=1 :
                flag = False
        if flag:
            listaPrimos.append(i)
    
    return listaPrimos

def verifyPrimo(i):
    #por definição, números primos são aqueles que são divisíveis somente por 2 números: 1 e ele mesmo
    #MAS existe uma definição extra que auxilia na identificação de primos muito extensos:
    #----Para verificar se um valor grande é primo, basta verificarmos se ele não é divisível
    #por nenhum valor primo que seja menor que sua raíz!

    listaPrimos = geraListaPrimos(round(math.sqrt(i)))
    flag = True

    for j in listaPrimos:
        if i%j==0 and j!=1 and j!=i:
            return False

    return True

def geraNroRand(a,b):
    listaNros = []
    for i in range(10):
        listaNros.append(random.randint(a,b))
    return listaNros

def multPrimos(listaNros):
    mul = 1

    for i in listaNros:
        if verifyPrimo(i):
            mul*=i
    
    return mul

#print(str(multPrimos(geraNroRand(20,50))))

#Nivel 2==================================================================================

def ladosTriangulo(a,b,c):
    #pontos a, b e c são encaminhados em tuplas no argumento
    print(str([math.sqrt(pow(a[-1]-b[-1],2)+pow(a[-2]-b[-2],2)),math.sqrt(pow(c[-1]-b[-1],2)+pow(c[-2]-b[-2],2)),math.sqrt(pow(a[-1]-c[-1],2)+pow(a[-2]-c[-2],2))]))

def angulosTriangulo(a,b,c):
    #podemos descobrir os 3 ângulos de um triângulo via lei dos cossenos!
    aglC = (numpy.arccos((a*a + b*b - c*c)/(2*a*b))*180)/math.pi
    aglB = (numpy.arccos((a*a + c*c - b*b)/(2*a*c))*180)/math.pi
    aglA = (numpy.arccos(((c*c) + (b*b) - (a*a))/(2*b*c))*180)/math.pi
    print(str([round(aglA,2),round(aglB,2),aglC]))

def perimetroTriangulo(a,b,c):
    print(str(a+b+c))

def areaTrianguloPtos(a,b,c):
    #podemos calcular a área do triângulo, de forma mais simples, pelo módulo do determinante
    #da matriz das coordenadas de seus vértices, dividido por 2 :)

    matrix = [[a[-1],a[-2],1],[b[-1],b[-2],1],[c[-1],c[-2],1]]
    print(str(abs(numpy.linalg.det(matrix))/2))

def areaTrianguloLados(a,b,c):
    #pela fórmula de Heron, podemos calcular a área do triângulo da seguinte forma:
    s = (a+b+c)/2
    print(math.sqrt(s*(s-a)*(s-b)*(s-c)))

def verifyTrianguloNotavel(a,b,c):
    #pode ser por comparação com lados ou ângulos!
    if a==b and a==c :
        print("Equilátero")
    elif a==b or a==c or b==c:
        print("Isósceles")
    else:
        printf("Escaleno")

def verifyAnguloTriangulo(a,b,c):
    if a == 90.0 or a==math.pi/2:
        print("Retângulo")
    elif a <90.0 and b<90.0 and c<90.0:
        print("Acutângulo")
    elif a>90.0 or b>90.0 or c>90.0:
        print("Obtusângulo")

#ladosTriangulo((0,0),(3,0),(0,4))
#areaTrianguloPtos((0,0),(3,0),(0,4))
#areaTrianguloLados(3,4,5)
#perimetroTriangulo(3.0,4.0,5.0)
#angulosTriangulo(3.0,4.0,5.0)
#verifyTrianguloNotavel(3,4,3)
#verifyAnguloTriangulo(90,45,45)
#verifyAnguloTriangulo(60,60,60)
#verifyAnguloTriangulo(120,30,30)
