import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;
import java.util.ArrayList;

public class JanelaLivro extends Janela{

    public JanelaLivro(ArrayList<Bibliografia> L){
        JFrame janL = new JFrame("");
        janL.setSize(400,200);

        JLabel Liv = new JLabel("Livros");
        Liv.setHorizontalAlignment(JLabel.CENTER);
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
                new JanelaRevista(L);
            }
        });

        JButton incluir = new JButton("Incluir");
        incluir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Incluir(new Livro(tL.getText(),aL.getText(),Integer.parseInt(anL.getText())),L);
                tL.setText("");
                aL.setText("");
                anL.setText("");
            }
        });

        JButton listagem =  new JButton("Listagem");
        listagem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Listagem(L);
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
        WindowListener listener = new WindowAdapter() {
            public void windowClosing(WindowEvent evt) {
                if(!L.isEmpty()) {
                    new DBPopulation().launchlivro(L);
                }
            }
        };
        janL.addWindowListener(listener);
        janL.setVisible(true);
    }

}
