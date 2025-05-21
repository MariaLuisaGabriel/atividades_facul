import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Livro extends Bibliografia{
    private String autor;
    public Livro(){}
    public Livro(String titulo, String autor, int ano){
        super(titulo,ano);
        this.autor = autor;
    }

    public String getAutor() {
        return autor;
    }

    public void JanelaL(Janela jan){
        JFrame janL = new JFrame("");
        janL.setSize(400,200);

        JLabel Liv = new JLabel("Livros");
        JLabel tit = new JLabel("Título:");
        JLabel aut = new JLabel("Autor:");
        JLabel an = new JLabel("Ano:");

        JPanel painelNorte = new JPanel(new GridLayout(3,2));
        JPanel painelSul = new JPanel();

        JTextField tL = new JTextField(30);//texto para título de livro/Revista
        JTextField aL = new JTextField(30);//texto para autor de livro
        JTextField anL = new JTextField(4);//texto para ano de livro/Revista

        JButton revistas =  new JButton("Revistas");
        revistas.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e) {
                janL.dispose();
                new Revista().JanelaR(jan);
            }
        });

        JButton incluir = new JButton("Incluir");
        incluir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                jan.Incluir(new Livro(tL.getText(),aL.getText(),Integer.parseInt(anL.getText())));
                tL.setText("");
                aL.setText("");
                anL.setText("");
            }
        });

        JButton listagem =  new JButton("Listagem");
        listagem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                jan.Listagem();
            }
        });

        painelNorte.add(tit);
        painelNorte.add(tL);
        painelNorte.add(aut);
        painelNorte.add(aL);
        painelNorte.add(an);
        painelNorte.add(anL);

        painelSul.add(incluir);
        painelSul.add(revistas);
        painelSul.add(listagem);

        janL.add(Liv);
        janL.add(painelNorte);
        janL.add(painelSul);

        janL.setLayout(new GridLayout(3,1));

        janL.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        janL.setVisible(true);
    }

    @Override
    public String Print(){
        return "Livro: "+titulo+" "+autor+" "+ano;
    }
}

