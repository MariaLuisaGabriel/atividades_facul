iris<-read.table(file="Iris.csv",header = T, sep = ",")


indices <- sample(1:nrow(iris),size = (nrow(iris)),replace = FALSE)
sample(150)
iris<-iris[indices,]
iris

n<-round(nrow(iris)*0.8) #pega 80% das iris
n
treinamento<-iris[1:n,] #separa 80% das iris
teste<-iris[(n+1):nrow(iris),] #deixa os 20% em outra variavel

setosa<-treinamento[treinamento$Species == "Iris-setosa",] # so as setosa
virginica<-treinamento[treinamento$Species == "Iris-virginica",] # so as virginica
versicolor<-treinamento[treinamento$Species == "Iris-versicolor",] # so as versicolor

#Analise das Petalas
boxplot(setosa$PetalLengthCm, versicolor$PetalLengthCm, virginica$PetalLengthCm, names = c("setosa","versicolor","virginica"))
boxplot(setosa$PetalWidthCm, versicolor$PetalWidthCm, virginica$PetalWidthCm, names = c("setosa","versicolor","virginica"))
#conclusao: ambas sao boas como variaveis para agrupamento

#Analise das sepalas
boxplot(setosa$SepalLengthCm, versicolor$SepalLengthCm, virginica$SepalLengthCm, names = c("setosa","versicolor","virginica"))
boxplot(setosa$SepalWidthCm, versicolor$SepalWidthCm, virginica$SepalWidthCm, names = c("setosa","versicolor","virginica"))
#conclusao: ambas não são boas como variaveis para agrupamento

#Analise
par(mfrow = c(1,1))
plot(treinamento$PetalLengthCm, y = treinamento$PetalWidthCm, pch = 8, cex = 0.5,type = 'n') # o 'n' permite a utilização do points()
points(setosa$PetalLengthCm,setosa$PetalWidthCm,col="green",pch=16)
points(virginica$PetalLengthCm,virginica$PetalWidthCm,col="orange",pch=16)
points(versicolor$PetalLengthCm,versicolor$PetalWidthCm,col="blue",pch=16)

