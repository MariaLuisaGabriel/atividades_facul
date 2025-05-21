import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;
import java.util.ArrayList;

public class JanelaRevista extends Janela{
    public JanelaRevista(ArrayList<Bibliografia> L){
        JFrame janR = new JFrame("");
        janR.setSize(400,200);

        JLabel Rev = new JLabel("Revistas");
        Rev.setHorizontalAlignment(JLabel.CENTER);
        JLabel tit = new JLabel("Título:");
        JLabel orgR = new JLabel("Organização:");
        JLabel anoR = new JLabel("Ano:");
        JLabel valR = new JLabel("Volume:");
        JLabel num = new JLabel("Número:");

        JPanel painelNorte = new JPanel(new GridLayout(2,2));
        JPanel painelSul = new JPanel();
        JPanel painelCentro = new JPanel();

        JTextField tR = new JTextField(30);//texto para título de revista
        JTextField o = new JTextField(30);//texto para organização de revista
        JTextField anR = new JTextField(4);//texto para ano de revista
        JTextField valT = new JTextField(4);//texto para valor de revista
        JTextField nro = new JTextField(4);//texto para numero de revista

        JButton livros =  new JButton("Livros");
        livros.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e) {
                janR.dispose();
                new JanelaLivro(L);
            }
        });

        JButton incluir = new JButton("Incluir");
        incluir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Incluir(new Revista(tR.getText(),o.getText(),Integer.parseInt(valT.getText()),Integer.parseInt(nro.getText()),Integer.parseInt(anR.getText())),L);
                tR.setText("");o.setText("");valT.setText("");nro.setText("");anR.setText("");
            }
        });

        JButton listagem =  new JButton("Listagem");
        listagem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Listagem(L);
            }
        });

        painelNorte.add(tit);
        painelNorte.add(tR);
        painelNorte.add(orgR);
        painelNorte.add(o);

        painelCentro.add(valR);
        painelCentro.add(valT);
        painelCentro.add(num);
        painelCentro.add(nro);
        painelCentro.add(anoR);
        painelCentro.add(anR);

        painelSul.add(incluir);
        painelSul.add(livros);
        painelSul.add(listagem);

        janR.add(Rev);
        janR.add(painelNorte);
        janR.add(painelCentro);
        janR.add(painelSul);

        janR.setLayout(new GridLayout(4,1));

        janR.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        WindowListener listener = new WindowAdapter() {
            public void windowClosing(WindowEvent evt) {
                if(!L.isEmpty()) {
                    new DBPopulation().launchrevista(L);
                }
            }
        };
        janR.addWindowListener(listener);
        janR.setVisible(true);
    }

}
