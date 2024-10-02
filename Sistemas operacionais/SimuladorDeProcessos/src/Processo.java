class Processo {
    int pid;            // Identificador do processo
    int tempoExecucao;  // Tempo de execução do processo para o SJF
    // int tempoChegada; // para o FIFO?
    public Processo(int pid, int tempoExecucao) {
        this.pid = pid;
        this.tempoExecucao = tempoExecucao;
    }

    @Override
    public String toString() {
        return "Processo [PID: " + pid + ", Tempo Execução: " + tempoExecucao + "]";
    }
}