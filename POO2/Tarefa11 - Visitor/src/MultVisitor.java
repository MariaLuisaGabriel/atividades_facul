import java.util.List;

public class MultVisitor implements NumberVisitor{
    @Override
    public void visit(TwoElement twoElement) {
        int sum = twoElement.a * twoElement.b;
        System.out.println(twoElement.a + "*" + twoElement.b + "=" + sum);
    }

    @Override
    public void visit(ThreeElement threeElement) {
        int sum = threeElement.a * threeElement.b * threeElement.c;
        System.out.println(threeElement.a + "*" + threeElement.b + "*" + threeElement.c +"=" + sum);
    }

    @Override
    public void visit(List<NumberElement> elementlist) {
        for(NumberElement ne : elementlist){
            ne.accept(this);
        }
    }
}
