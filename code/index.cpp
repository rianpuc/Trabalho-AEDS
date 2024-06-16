#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

class Paciente{
    private:
        std::string codigo, nome, endereco, telefone, data_nascimento;
    public:
        Paciente(std::string& cod, const std::string& nom, const std::string& end, const std::string& tel, const std::string& data_nasc)
        : codigo(cod), nome(nom), endereco(end), telefone(tel), data_nascimento(data_nasc) {}
        ~Paciente() = default;
        std::string getCodigo() const { 
            return codigo; }
        std::string getNome() const { 
            return nome; }
        std::string getEndereco() const { 
            return endereco; }
        std::string getTelefone() const { 
            return telefone; }
        std::string getDataNascimento() const { 
            return data_nascimento; }
        void exibir() const {
            std::cout << "Código: " << codigo << "\n" << "Nome: " << nome << "\n" << "Endereço: " << endereco << "\n" << "Telefone: " << telefone << "\n" << "Data de Nascimento: " << data_nascimento << "\n"; }
};

class Medico{
    private:
        std::string codigo, nome, especialidade, telefone;
    public:
        Medico(std::string &codigo, std::string &nome, std::string &especialidade, std::string &telefone)
            : codigo(codigo), nome(nome), especialidade(especialidade), telefone(telefone) {}
        ~Medico() = default;
        std::string getCodigo() const { 
            return this->codigo; }
        std::string getNome() const { 
            return this->nome; }
        std::string getEspecialidade() const { 
            return this->especialidade; }
        std::string getTelefone() const { 
            return this->telefone; }
        void exibir() const{
            std::cout << "Codigo: " << codigo << std::endl
                    << "Nome: " << nome << std::endl
                    << "Especialidade: " << especialidade << std::endl
                    << "Telefone: " << telefone << std::endl;
        }
};

class Consulta{
    private:
        std::string codigo, data, hora, cod_medico, cod_paciente;
    public:
        Consulta(std::string& cod, const std::string& data, const std::string& hora, const std::string& cod_med, const std::string& cod_pac)
        : codigo(cod), data(data), hora(hora), cod_medico(cod_med), cod_paciente(cod_pac) {}
        ~Consulta() = default;
        std::string getCodigo() const { 
            return codigo; }
        std::string getData() const { 
            return data; }
        std::string getHora() const { 
            return hora; }
        std::string getCodMed() const { 
            return cod_medico; }
        std::string getCodPac() const { 
            return cod_paciente; }
        void exibir() const {
            std::cout << "Código: " << codigo << "\n" << "Data: " << data << "\n" << "Hora: " << hora << "\n" << "Codigo Medico: " << cod_medico << "\n" << "Codigo Paciente: " << cod_paciente << "\n"; }
};

std::vector<Paciente> lerPacientes(const std::string&);
std::vector<Medico> lerMedicos(const std::string&);
std::vector<Consulta> lerConsultas(const std::string&);
void cadastrar_paciente(const std::string&);
void cadastrar_medico();
void cadastrar_consulta();
void cancelar_consulta();
void relatorios();
int converteHoraPraMinutos(const std::string&);
int converterDataPraNumero(const std::string&);
bool verificarMenorData(const std::string&, const std::string&);
bool verificarHoraValida(const std::string&, const std::string&);
bool verificarCadastroMedico(const std::string&, const std::string&);
bool verificarCadastroPaciente(const std::string&, const std::string&);
std::string obterDataAtual();
std::string gerarCodigo();
Paciente* buscarPaciente(const std::string&, std::vector<Paciente>&);
Medico* buscarMedico(const std::string&, std::vector<Medico>&);

int main(void){
    std::string arqPacientes = "pacientes.txt";
    std::string arqMedicos = "medicos.txt";
    std::string arqConsultas = "consultas.txt";
    int a;
    std::vector<Paciente> pacientes = lerPacientes(arqPacientes);
    std::vector<Medico> medicos = lerMedicos(arqMedicos);
    std::vector<Consulta> consultas = lerConsultas(arqConsultas);
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n[1] - Cadastrar um paciente\n[2] - Cadastrar um medico\n[3] - Cadastrar uma consulta\n";
    std::cout << "[4] - Cancelar uma consulta\n[5] - Relatorios\n[0] - Sair\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\nSelecione uma opcao: ";
    std::cin >> a;
    switch (a){
        case 1:
            cadastrar_paciente(arqPacientes);
            break;
        case 2:
            cadastrar_medico();
            break;
        case 3:
            cadastrar_consulta();
            break;
        case 4:
            cancelar_consulta();
            break;
        case 5:
            relatorios();
            break;
        case 0:
            return 0;
            break;
        default:
            main();
            break;
    }
}

std::vector<Paciente> lerPacientes(const std::string& nomeArquivo){
    std::ifstream arquivo(nomeArquivo);
    if(!arquivo.is_open()){
        std::ofstream arquivo(nomeArquivo);
    }
    std::vector<Paciente> pacientes;
    std::string codigo, nome, endereco, telefone, data_nascimento;
    while(std::getline(arquivo, codigo) &&
           std::getline(arquivo, nome) &&
           std::getline(arquivo, endereco) &&
           std::getline(arquivo, telefone) &&
           std::getline(arquivo, data_nascimento)){
        if(arquivo.fail()){
            exit(EXIT_FAILURE);
        }
        pacientes.emplace_back(codigo, nome, endereco, telefone, data_nascimento);
    }
    arquivo.close();
    return pacientes;
}

std::vector<Medico> lerMedicos(const std::string& nomeArquivo){
    std::ifstream arquivo(nomeArquivo);
    if(!arquivo.is_open()){
        std::ofstream arquivo(nomeArquivo);
    }
    std::vector<Medico> medicos;
    std::string codigo, nome, especialidade, telefone;
    while(std::getline(arquivo, codigo) &&
           std::getline(arquivo, nome) &&
           std::getline(arquivo, especialidade) &&
           std::getline(arquivo, telefone)){
        if(arquivo.fail()){
            exit(EXIT_FAILURE);
        }
        medicos.emplace_back(codigo, nome, especialidade, telefone);
    }
    arquivo.close();
    return medicos;
}

std::vector<Consulta> lerConsultas(const std::string& nomeArquivo){
    std::ifstream arquivo(nomeArquivo);
    if(!arquivo.is_open()){
        std::ofstream arquivo(nomeArquivo);
    }
    std::vector<Consulta> consultas;
    std::string codigo, data, hora, cod_medico, cod_paciente;
    while(std::getline(arquivo, codigo) &&
           std::getline(arquivo, data) &&
           std::getline(arquivo, hora) &&
           std::getline(arquivo, cod_medico) &&
           std::getline(arquivo, cod_paciente)){
        if(arquivo.fail()){
            exit(EXIT_FAILURE);
        }
        consultas.emplace_back(codigo, data, hora, cod_medico, cod_paciente);
    }
    arquivo.close();
    return consultas;
}

void cadastrar_paciente(const std::string& nomeArquivo){
    std::cin.ignore();
    std::ofstream arquivo(nomeArquivo, std::ios::app);
    std::string codigo = gerarCodigo();
    std::string nome, endereco, telefone, data_nascimento;
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Endereço: ";
    std::getline(std::cin, endereco);
    std::cout << "Telefone: ";
    std::getline(std::cin, telefone);
    std::cout << "Data de Nascimento (DD/MM/AAAA): ";
    std::getline(std::cin, data_nascimento);
    arquivo << codigo << "\n" << nome << "\n" << endereco << "\n" << telefone << "\n" << data_nascimento << "\n";
    arquivo.close();
    main();
}

void cadastrar_medico(){
    std::string codigo = gerarCodigo();
    std::string nome, especialidade, telefone;
    std::cin.ignore();
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Especialidade: ";
    std::getline(std::cin, especialidade);
    std::cout << "Telefone: ";
    std::getline(std::cin, telefone);
    Medico novoMedico(codigo, nome, especialidade, telefone);
    novoMedico.exibir();
}

void cadastrar_consulta(){
    std::cout << "\nCadastrar consulta\n";
}

void cancelar_consulta(){
    std::cout << "\nCancelar consulta\n";
}

void relatorios(){
    std::cout << "\nRelatorios\n";
}

int converteHoraPraMinutos(const std::string& hora){
    int horas, minutos;
    char delim;
    std::istringstream ss(hora);
    ss >> horas >> delim >> minutos;
    return horas * 60 + minutos;
}

int converterDataPraNumero(const std::string& data){
    int dia, mes, ano;
    char delim;
    std::istringstream ss(data);
    ss >> dia >> delim >> mes >> delim >> ano;
    return ano * 10000 + mes * 100 + dia;
}

bool verificarMenorData(const std::string& data1, const std::string& data2){
    int num_data1 = converterDataPraNumero(data1);
    int num_data2 = converterDataPraNumero(data2);
    return num_data1 < num_data2;
}

bool verificarHoraValida(const std::string& hora1, const std::string& hora2){
    int minutos1 = converteHoraPraMinutos(hora1);
    int minutos2 = converteHoraPraMinutos(hora2);
    int diferenca = std::abs(minutos1 - minutos2);
    return diferenca >= 30;
}

bool verificarCadastroMedico(const std::string& entrada, const std::string& nomeArquivo) {
    std::vector<Medico> medicosCadastrados = lerMedicos(nomeArquivo);
    Medico* medico = buscarMedico(entrada, medicosCadastrados);
    return medico != nullptr;
}; 

bool verificarCadastroPaciente(const std::string& entrada, const std::string& nomeArquivo) {
    std::vector<Paciente> pacientesCadastrados = lerPacientes(nomeArquivo);
    Paciente* paciente = buscarPaciente(entrada, pacientesCadastrados);
    return paciente != nullptr;
}; 

Paciente* buscarPaciente(const std::string& entrada, std::vector<Paciente>& dados) {
    for (Paciente& paciente : dados) {
        if (paciente.getNome() == entrada || paciente.getCodigo() == entrada)
            return &paciente;
    }

    return nullptr;
};

Medico* buscarMedico(const std::string& entrada, std::vector<Medico>& dados) {
  for (Medico& medico : dados) {
        if (medico.getNome() == entrada || medico.getCodigo() == entrada)
            return &medico;
    }

    return nullptr;  
};

std::string obterDataAtual(){
    auto agora = std::chrono::system_clock::now();
    std::time_t tempo_atual = std::chrono::system_clock::to_time_t(agora);
    std::tm *tm_atual = std::localtime(&tempo_atual);
    std::ostringstream data_formatada;
    data_formatada << std::setfill('0') << std::setw(2) << tm_atual->tm_mday << "/"
                   << std::setfill('0') << std::setw(2) << (tm_atual->tm_mon + 1) << "/"
                   << (tm_atual->tm_year + 1900);
    return data_formatada.str();
}

std::string gerarCodigo(){
    auto agora = std::chrono::system_clock::now();
    auto duracao = agora.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duracao).count();
    return std::to_string(millis);
}
