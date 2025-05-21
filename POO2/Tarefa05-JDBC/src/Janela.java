import javax.swing.*;
import java.util.ArrayList;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;

public abstract class Janela {
    public void Incluir(Bibliografia b,ArrayList<Bibliografia> L){ L.add(b); }
    public void Listagem(ArrayList<Bibliografia> L){
        JFrame janList = new JFrame("Listagem de Bibliografias..");
        janList.setSize(400,200);

        String List = "";
        for(int i = 0; i<L.size(); i++){
            List += L.get(i).Print()+"\n";
        }
        janList.add(new JTextArea(List));

        janList.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        WindowListener listener = new WindowAdapter() {
            public void windowClosing(WindowEvent evt) {
                DBPopulation p = new DBPopulation();
                if(!L.isEmpty()) {
                    p.launchlivro(L);
                    p.launchrevista(L);
                }
            }
        };
        janList.addWindowListener(listener);
        janList.setVisible(true);
    }
}
