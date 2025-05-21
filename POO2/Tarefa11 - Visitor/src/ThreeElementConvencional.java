public class ThreeElementConvencional extends NumberElementConvencional{
    private int a,b,c;

    public ThreeElementConvencional(int a, int b, int c){
        this.a = a;
        this.b = b;
        this.c = c;
    }

    @Override
    public int sum() {
        int sum = a+b+c;
        System.out.println(a + "+" + b + "+" + c + "=" + sum);
        return sum;
    }
}
