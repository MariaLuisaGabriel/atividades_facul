public class Animal {
    Animal(){}
    public void walk(){}

    public void eat(){}
}

//extract subclass !!!
//meow() era um método específico para certos animais, diferentemente de walk() e eat(), por isso foi transferido
//para uma subclasse chamada Cat, onde todos os objetos de lá instanciados realmente possuem esse comportamento.