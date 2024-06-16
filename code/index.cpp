#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

class Paciente{
    private:
        std::string codigo;
        std::string nome;
        std::string endereco;
        std::string telefone;
        std::string data_nascimento;
    
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
    const std::string codigo, nome, especialidade;
    std::string telefone;

public:
    Medico(const std::string &codigo, const std::string &nome, const std::string &especialidade, const std::string &telefone)
        : codigo(codigo), nome(nome), especialidade(especialidade), telefone(telefone) {}
    Medico(const std::string &codigo, const std::string &nome, const std::string &especialidade)
        : codigo(codigo), nome(nome), especialidade(especialidade), telefone(""){};

    void setTelefone(const std::string &telefone)
    {
        this->telefone = telefone;
    };

    std::string getCodigo() const { return this->codigo; }
    std::string getNome() const { return this->nome; }
    std::string getEspecialidade() const { return this->especialidade; }
    std::string getTelefone() const { return this->telefone; }

    void exibir() const
    {
        std::cout << "Codigo: " << codigo << std::endl
                  << "Nome: " << nome << std::endl
                  << "Especialidade: " << especialidade << std::endl
                  << "Telefone: " << telefone << std::endl;
    }
};

class Consulta{
    private:
        std::string codigo;
        std::string data;
        std::string hora;
        std::string cod_medico;
        std::string cod_paciente;
    
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
std::string gerarCodigo();

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
    Paciente novoPaciente(codigo, nome, endereco, telefone, data_nascimento);
    arquivo << codigo << "\n" << nome << "\n" << endereco << "\n" << telefone << "\n" << data_nascimento << "\n";
    arquivo.close();
    main();
}

void cadastrar_medico(){
    const std::string codigo = gerarCodigo();
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

std::string gerarCodigo(){
    using namespace std::chrono;
    auto agora = system_clock::now();
    auto duracao = agora.time_since_epoch();
    auto millis = duration_cast<milliseconds>(duracao).count();
    return std::to_string(millis);
}
