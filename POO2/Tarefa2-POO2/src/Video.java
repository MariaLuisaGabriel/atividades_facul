public class Video extends Bibliografia{
    public Video(String titulo, String autor, int ano, String duracao){
        super(titulo,ano);
        this.autor = autor;
        this.duracao = duracao;
    }
    private String autor;
    private String duracao;

    public String getAutor() {
        return autor;
    }

    public String getDuracao() {
        return duracao;
    }

    @Override
    public String Print(){return "Video: "+titulo+" "+autor+" "+duracao+" "+ano;}
}
