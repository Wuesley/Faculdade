class Processo {


    int p_id;
    int tempoExecucao;
    int tempoChegada;
    int tempoTotalExecucao;


    public Processo(int p_id, int tempoExecucao) {
        this.p_id = p_id;
        this.tempoExecucao = tempoExecucao;
    }

    @Override
    public String toString() {
        return "Processo [PID: " + p_id + ", Tempo Execução: " + tempoExecucao + "]";
    }
}