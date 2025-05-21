import java.util.List;

public class TotalSumVisitor implements NumberVisitor{
    private int TotalSum = 0;
    @Override
    public void visit(TwoElement twoElement) {
        int sum = twoElement.a + twoElement.b;
        System.out.println("adding " + sum);
        TotalSum += sum;
    }
    @Override
    public void visit(ThreeElement threeElement) {
        int sum = threeElement.a + threeElement.b + threeElement.c;
        System.out.println("adding " + sum);
        TotalSum += sum;
    }
    @Override
    public void visit(List<NumberElement> elementlist) {
        for(NumberElement ne : elementlist){
            ne.accept(this);
        }
    }
    public int getTotalSum() {
        return TotalSum;
    }
}
