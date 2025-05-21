import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Livro extends Bibliografia{
    private String autor;
    public Livro(String titulo, String autor, int ano){
        super(titulo,ano);
        this.autor = autor;
    }
    public String getAutor() {
        return autor;
    }
    @Override
    public String Print(){
        return "Livro: "+titulo+" "+autor+" "+ano;
    }
}

