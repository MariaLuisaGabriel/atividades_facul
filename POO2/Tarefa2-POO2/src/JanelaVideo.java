import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class JanelaVideo extends Janela{
    public JanelaVideo(ArrayList<Bibliografia> L) {
        JFrame janV = new JFrame("");
        janV.setSize(400,200);

        JLabel Vid = new JLabel("Videos");
        Vid.setHorizontalAlignment(JLabel.CENTER);
        JLabel tit = new JLabel("Título:");
        JLabel aut = new JLabel("Autor:");
        JLabel anoV = new JLabel("Ano:");
        JLabel dur = new JLabel("Duração:");

        JPanel painelCentro = new JPanel(new GridLayout(4,2));
        JPanel painelSul = new JPanel();
        JPanel painelNorte = new JPanel();

        JTextField tV = new JTextField(30);//texto para título de revista
        JTextField aV = new JTextField(30);//texto para autor de revista
        JTextField anV = new JTextField(4);//texto para ano de revista
        JTextField durV = new JTextField(10);//texto para duracao de revista

        JButton livros =  new JButton("Livros");
        livros.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e) {
                janV.dispose();
                new JanelaLivro(L);
            }
        });

        JButton revistas =  new JButton("Revistas");
        revistas.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e) {
                janV.dispose();
                new JanelaRevista(L);
            }
        });

        JButton incluir = new JButton("Incluir");
        incluir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Incluir(new Video(tV.getText(),aV.getText(),Integer.parseInt(anV.getText()),durV.getText()),L);
                tV.setText("");aV.setText("");durV.setText("");anV.setText("");
            }
        });

        JButton listagem =  new JButton("Listagem");
        listagem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Listagem(L);
            }
        });

        painelCentro.add(tit);
        painelCentro.add(tV);
        painelCentro.add(aut);
        painelCentro.add(aV);
        painelCentro.add(anoV);
        painelCentro.add(anV);
        painelCentro.add(dur);
        painelCentro.add(durV);

        painelSul.add(incluir);
        painelSul.add(livros);
        painelSul.add(revistas);
        painelSul.add(listagem);

        janV.add(Vid);
        janV.add(painelCentro);
        janV.add(painelSul);

        janV.setLayout(new GridLayout(4,1));

        janV.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        janV.setVisible(true);
    }
}
