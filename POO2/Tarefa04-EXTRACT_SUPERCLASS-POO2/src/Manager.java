public class Manager extends Staff{
    private double bonus;

    public Manager(String name, String email, double salary, double bonus) {
        super(name, email, salary);
        this.bonus = bonus;
    }
}
