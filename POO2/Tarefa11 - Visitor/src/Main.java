import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        /*TwoElement twe = new TwoElement(1,2);
        ThreeElement the = new ThreeElement(1,2,3);

        SumVisitor sv = new SumVisitor();
        TotalSumVisitor tsv = new TotalSumVisitor();
        MultVisitor mv = new MultVisitor();
        TotalMultSumVisitor tmsv = new TotalMultSumVisitor();

        List<NumberElement> Lnv = new ArrayList<>();
        Lnv.add(twe);
        Lnv.add(the);

        sv.visit(Lnv);
        tsv.visit(Lnv);

        mv.visit(Lnv);
        tmsv.visit(Lnv);

        System.out.println("TOTAL SUM = " + tsv.getTotalSum());
        System.out.println("TOTAL MULT SUM = " + tmsv.getTSum());*/

        System.out.println("MÉTODO CONVENCIONAL");
        TwoElementConvencional twec = new TwoElementConvencional(1,2);
        ThreeElementConvencional thec = new ThreeElementConvencional(1,2,3);

        List<NumberElementConvencional> Lnvc = new ArrayList<>();
        Lnvc.add(twec);
        Lnvc.add(thec);

        int sum = 0;
        for(NumberElementConvencional nec : Lnvc){
            sum += nec.sum();
        }
        System.out.println("total sum: "+sum);

    }
}