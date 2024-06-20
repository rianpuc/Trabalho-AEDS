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
void cadastrar_medico(const std::string&);
void cadastrar_consulta(const std::string&);
void cancelar_consulta();
void relatorios();
int converteHoraPraMinutos(const std::string&);
int converterDataPraNumero(const std::string&);
bool verificarMenorData(const std::string&, const std::string&);
bool verificarHoraValida(const std::string&, const std::string&);
bool verificarCadastroMedico(const std::string&, std::vector<Medico>&);
bool verificarCadastroPaciente(const std::string&, std::vector<Paciente>&);
bool verificarQuantidadeConsultasMedico(const std::string&, const Medico&);
bool verificarHorarioDisponivelMedico(const std::string&, const std::string&, const Medico&);
std::string obterDataAtual();
std::string gerarCodigo();
Paciente* buscarPaciente(const std::string&, std::vector<Paciente>&);
Medico* buscarMedico(const std::string&, std::vector<Medico>&);
std::vector<Consulta> buscarConsultasPelaData(const std::string&, const Medico&);

std::string arqPacientes = "pacientes.txt";
std::string arqMedicos = "medicos.txt";
std::string arqConsultas = "consultas.txt";

int main(void){
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
            cadastrar_medico(arqMedicos);
            break;
        case 3:
            cadastrar_consulta(arqConsultas);
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

void cadastrar_medico(const std::string& nomeArquivo){
    std::cin.ignore();
    std::ofstream arquivo(nomeArquivo, std::ios::app);
    std::string codigo = gerarCodigo();
    std::string nome, especialidade, telefone;
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Especialidade: ";
    std::getline(std::cin, especialidade);
    std::cout << "Telefone: ";
    std::getline(std::cin, telefone);
    arquivo << codigo << "\n" << nome << "\n" << especialidade << "\n" << telefone << "\n";
    arquivo.close();
    main();
}

void cadastrar_consulta(const std::string& nomeArquivo){
    std::cin.ignore();
    std::string codigo = gerarCodigo();
    std::string data, hora, nome_do_medico, nome_do_paciente, cod_medico, cod_paciente;
    std::cout << "Data (DD/MM/YYYY): ";
    std::getline(std::cin, data);
    std::cout << "Hora (hh:mm): ";
    std::getline(std::cin, hora);
    std::cout << "Nome do Medico: ";
    std::getline(std::cin, nome_do_medico);
    std::cout << "Nome do Paciente: ";
    std::getline(std::cin, nome_do_paciente);
    std::vector<Paciente> pacientes = lerPacientes(arqPacientes);
    std::vector<Medico> medicos = lerMedicos(arqMedicos);
    std::vector<Consulta> consultas = lerConsultas(arqConsultas);
    if(verificarCadastroMedico(nome_do_medico, medicos) == true){
        Medico* medico = buscarMedico(nome_do_medico, medicos);
        cod_medico = medico->getCodigo();
    } else {
        std::cout << "Esse medico nao esta cadastrado!\n";
    }

    if(verificarCadastroPaciente(nome_do_paciente, pacientes) == true){
        Paciente* paciente = buscarPaciente(nome_do_paciente, pacientes);
        cod_paciente = paciente->getCodigo();
    } else {
        std::cout << "Esse paciente nao esta cadastrado!\n";
    }

    if(verificarCadastroMedico(nome_do_medico, medicos) == true && verificarCadastroPaciente(nome_do_paciente, pacientes) == true){
        std::ofstream arquivo(nomeArquivo, std::ios::app);
        arquivo << codigo << "\n" << data << "\n" << hora << "\n" << cod_medico << "\n" << cod_paciente << "\n";
        arquivo.close();
    }
    main();
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

bool verificarCadastroMedico(const std::string& entrada, std::vector<Medico>& dados) {
    Medico* medico = buscarMedico(entrada, dados);
    return medico != nullptr;
}; 

bool verificarCadastroPaciente(const std::string& entrada, std::vector<Paciente>& dados) {
    Paciente* paciente = buscarPaciente(entrada, dados);
    return paciente != nullptr;
}; 

bool verificarQuantidadeConsultasMedico(const std::string& data, const Medico& medico) {
    std::vector<Consulta> consultasMedico = buscarConsultasPelaData(data, medico);
    return consultasMedico.size() < 2;
}

bool verificarHorarioDisponivelMedico(const std::string& horario, const std::string& data, const Medico& medico) {
    if (verificarQuantidadeConsultasMedico(data, medico) == false)
        return false;
    std::vector<Consulta> consultasMedico = buscarConsultasPelaData(data, medico);
    Consulta& consulta = consultasMedico.at(0);
    int horarioConsulta = converteHoraPraMinutos(consulta.getHora());
    int horarioNovaConsulta = converteHoraPraMinutos(horario);
    int intervalo = horarioConsulta - horarioNovaConsulta;
    return intervalo >= 30 || intervalo <= -30;
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

std::vector<Consulta> buscarConsultasPelaData(const std::string& data, const Medico& medico) 
{
    std::vector<Consulta> consultasCadastradas = lerConsultas(arqConsultas);
    std::vector<Consulta> consultas;
    for (Consulta& consulta : consultasCadastradas)
        if (consulta.getCodMed() == medico.getCodigo() && consulta.getData() == data)
            consultas.push_back(consulta);

    return consultas;
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
