public class TwoElementConvencional extends NumberElementConvencional{

    private int a,b;
    public TwoElementConvencional(int a, int b){
        this.a = a;
        this.b = b;
    }

    @Override
    public int sum() {
        int sum = a+b;
        System.out.println(a + "+" + b + "=" + sum);
        return sum;
    }
}
