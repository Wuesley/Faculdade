class Processo {


    int p_id;
    int tempoExecucao;
    int tempoChegada;
    private State state;

    public Processo(int p_id, int tempoChegada, int tempoExecucao) {
        this.p_id = p_id;
        this.tempoChegada = tempoChegada;
        this.tempoExecucao = tempoExecucao;
    }

    public int getP_id() {
        return p_id;
    }

    public void setP_id(int p_id) {
        this.p_id = p_id;
    }

    public int getTempoExecucao() {
        return tempoExecucao;
    }

    public void setTempoExecucao(int tempoExecucao) {
        this.tempoExecucao = tempoExecucao;
    }

    public int getTempoChegada() {
        return tempoChegada;
    }

    public void setTempoChegada(int tempoChegada) {
        this.tempoChegada = tempoChegada;
    }

    public State getState() {
        return state;
    }

    public void setState(State state) {
        this.state = state;
    }

    @Override
    public String toString() {
        return "Processo{" +
                "p_id=" + p_id +
                ", tempoExecucao=" + tempoExecucao +
                ", tempoChegada=" + tempoChegada +
                ", state=" + state +
                '}';
    }
}