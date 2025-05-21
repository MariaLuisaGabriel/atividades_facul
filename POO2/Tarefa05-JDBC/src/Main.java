import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        //new DBConfiguration().launch(); //configura o banco
        ArrayList<Bibliografia> L = new ArrayList<>();
        new DBListing().launchlivro(L); //pega todos os dados já existentes na persistência
        new DBListing().launchrevista(L); //pega todos os dados já existentes na persistência
        new JanelaLivro(L);
    }
}
