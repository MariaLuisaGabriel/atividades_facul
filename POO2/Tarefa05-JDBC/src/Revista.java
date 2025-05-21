import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Revista extends Bibliografia{
    private String org;
    private int numero;
    private int vol;

    public Revista(String titulo, String org, int vol, int nro, int ano){
        super(titulo,ano);
        this.org = org;
        this.vol = vol;
        numero = nro;
    }

    public int getNumero() {
        return numero;
    }

    public int getVol() {
        return vol;
    }

    public String getOrg() {
        return org;
    }

    @Override
    public String Print(){
        return "Revista: "+titulo+" "+org+" "+vol+" "+numero+" "+ano;
    }
}
