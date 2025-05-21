public class Bibliografia {
    protected String titulo;
    protected int ano;
    public Bibliografia(){}
    public Bibliografia(String titulo, int ano){
        this.ano = ano;
        this.titulo = titulo;
    }

    public int getAno() {
        return ano;
    }

    public String getTitulo() {
        return titulo;
    }

    public String Print(){return "";}
}
