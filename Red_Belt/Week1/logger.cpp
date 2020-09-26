#include <string>
#include <ostream>
using namespace std;

class Logger {
public:
	explicit Logger(ostream& output_stream) : os(output_stream) {}

	void SetLogLine(bool value) { log_line = value; }
	void SetLogFile(bool value) { log_file= value; }

	void Log(const string& message) {
		if (log_file && log_line) {
			os << file << ':' << line << ' ';
		} else if (log_line) {
			os << "Line " << line << ' ';
		} else if (log_file) {
			os << file << ' ';
		}
		os << message << '\n';
	}

	void ReceiveLine(int line_number) { line = line_number; }
	void ReceiveFile(const string& filename) { file = filename; }
private:
	ostream& os;
	bool log_line = false;
	bool log_file = false;
	int line;
	string file;
};

#define LOG(logger, message) \
  logger.ReceiveLine(__LINE__);  	\
  logger.ReceiveFile(__FILE__);  	\
  logger.Log(message);