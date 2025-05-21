#EXERCÍCIO 06 -  ANÁLISE DE COMPONENTES
attach(dados_tarefa)
data <- dados_tarefa[,2:4]

#a)--------------------------------------
#matriz de covariância
S<-cov(data)
S

#                        PercentualdeImportância SalárioMédio ConsumoMédio
#PercentualdeImportância                187.3929     -315.438     4529.727
#SalárioMédio                          -315.4380    23118.277   -15863.343
#ConsumoMédio                          4529.7274   -15863.343   123635.016

#matriz de correlação
R<-cor(data)
R

#                        PercentualdeImportância SalárioMédio ConsumoMédio
#PercentualdeImportância               1.0000000   -0.1515513    0.9410762
#SalárioMédio                         -0.1515513    1.0000000   -0.2967196
#ConsumoMédio                          0.9410762   -0.2967196    1.0000000

#autovalores e autovetores da matriz de correlação
auto<-eigen(R)
auto

#eigen() decomposition
#$values
#[1] 2.0383385 0.9144488 0.0472127

#$vectors
#           [,1]      [,2]       [,3]
#[1,]  0.6651648 0.2877859  0.6890102
#[2,] -0.2933117 0.9492755 -0.1133328
#[3,]  0.6866760 0.1267098 -0.7158356

#b)-------------------------
#componentes:

#Y1 = 0.6651*Importância - 0.2933*Salário + 0.6866*ConsumoMédio

#Y2 = 0.2878*Importância + 0.9493*Salário + 0.1267*ConsumoMédio

#Y3 = 0.6890*Importância - 0.1133*Salário - 0.7158*ConsumoMédio

#c)-------------------
#cálculo das porcentagens de variância de cada componente:

traço <- sum(auto$values) # = 3

porcentagemY1 <- auto$values[1]/traço # ~ 67,9%
porcentagemY1

porcentagemY2 <- auto$values[2]/traço # ~ 30,5%
porcentagemY2

porcentagemY3 <-auto$values[3]/traço # ~ 1,6%
porcentagemY3

#d)---------------------------
#interpretação e descarte de componentes

#por conceito, serão úteis à análise todos os componentes que, somadas as suas porcentagens,
#se mostram capazes de explicar 70% ou mais do comportamento das variáveis

#podemos ver que as porcentagens de Y1 e Y2 somadas já extrapolam os 70%, dizendo assim que Y3
#será descartado e as outras duas serão selecionadas para análise

#e)----------------------
#interpretando os componentes:

#Y1 reflete mais o comportamento da taxa de importância e do consumo médio, tendo em vista do valor
#de seus coeficientes, enquanto o salário tem pouco peso no valor de Y1

#Y2, ao contrário de Y1, reflete muito do comportamento do salário, visto que o valor de seu coeficiente é 
#bem mais alto do que o da importância e do consumo médio

#Y3 reflete o comportamento direto da importância, e inverso do consumo médio, visto que ambos possuem valores
#absolutos de coeficiente altos, sendo o do consumo médio negativo

#f)---------------------
#calculando escores dos componentes

compV <- princomp(data, cor = TRUE)
compV

#Standard deviations:
#  Comp.1    Comp.2    Comp.3 
#1.4277039 0.9562682 0.2172848 

# 3  variables and  8 observations.

compV$loadings

#              Comp.1 Comp.2 Comp.3
#SS loadings     1.000  1.000  1.000
#Proportion Var  0.333  0.333  0.333
#Cumulative Var  0.333  0.667  1.000

compV$scores

#        Comp.1      Comp.2      Comp.3
#[1,] -1.4510596  0.46072743 -0.17820259
#[2,] -1.1902530  0.51775963 -0.08204007
#[3,] -1.4980118  0.05639448 -0.21674781
#[4,]  0.2182300 -0.65068903  0.05614367
#[5,] -0.4336942 -1.37840606  0.19605972
#[6,]  2.9636700 -0.48675286 -0.31655956
#[7,]  0.1693787 -0.51949834  0.31486412
#[8,]  1.2217398  2.00046476  0.22648253

#CONCLUSÕES: cliente 6 possui o maior aproveitamento dos componentes(tem o maior escore),
#enquanto o cliente 3 possui o menor (tem o menor escore).

#EXERCÍCIO 07 - ANÁLISE DE AGRUPAMENTOS

dataG <- scale(data)

#a)--------------------------

#matriz de distâncias
Mdist <- dist(dataG)

#agrupamento por método das médias
grouping <- hclust(Mdist, method = "median")

#dendrograma
plot(grouping)

#pelo dendrograma, concluímos que os clientes 1 e 2 são os mais próximos entre si,
#e os clientes 6 e 8 se distanciam mais dos outros clientes, mas se agrupam

#b)------------------------------------
#método das k-médias, com 2 grupos

groupingK <- Kmeans(dataG,2)

#por esse agrupamento se conclui novamente a distanciação dos clientes 6 e 8 com os demais, 
#já que formam um grupo só entre eles
