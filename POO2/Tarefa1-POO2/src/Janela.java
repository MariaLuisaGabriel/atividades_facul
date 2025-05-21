import javax.swing.*;
import java.awt.event.*;
import java.util.ArrayList;

public class Janela {
    ArrayList<Bibliografia> L = new ArrayList<Bibliografia>();
    public Janela(){ }
    public void Incluir(Livro l){
        L.add(l);
    }
    public void Incluir(Revista r){
        L.add(r);
    }
    public void Listagem(){
        JFrame janList = new JFrame("Listagem de Livros/Revistas..");
        janList.setSize(400,200);

        String List = "";
        for(int i = 0; i<L.size(); i++){
            List += L.get(i).Print()+"\n";
        }
        janList.add(new JTextArea(List));

        janList.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        janList.setVisible(true);
    }
    public static void main(String[] args) {
        Janela jan = new Janela();//para o livro e a revista atualizarem o mesmo arraylist!
        new Livro().JanelaL(jan);
    }
}
