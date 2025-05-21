import java.util.List;

public class TotalMultSumVisitor implements NumberVisitor{
    private int tSum = 0;
    @Override
    public void visit(TwoElement twoElement) {
        int sum = twoElement.a * twoElement.b;
        System.out.println("adding "+twoElement.a + "*" + twoElement.b + "=" + sum);
        tSum+=sum;
    }
    @Override
    public void visit(ThreeElement threeElement) {
        int sum = threeElement.a * threeElement.b * threeElement.c;
        System.out.println("adding "+threeElement.a + "*" + threeElement.b + "*" + threeElement.c +"=" + sum);
        tSum+=sum;
    }
    @Override
    public void visit(List<NumberElement> elementlist) {
        for(NumberElement ne : elementlist){
            ne.accept(this);
        }
    }
    public int getTSum() {
        return tSum;
    }
}
