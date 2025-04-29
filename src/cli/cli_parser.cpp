#include "cli_parser.hpp"

namespace cli {

CLIParser::CLIParser() 
    : m_cli11("prng-bench", "Quant-style PRNG benchmarking tool") 
{   
    m_cli11.add_option("-i, --iterations", m_args.iterations, "Number of iterations per thread for the PRNGs to run. If running on 1 thread: iterations * numThreads = iterations for single thread.")
        ->default_str(std::to_string(cli::iterations));

    m_cli11.add_option("-t, --threads", m_args.numThreads, "Number of threads for multithread operations. If number is higher than available, this will change to available threads.")
        ->default_str(std::to_string(cli::numThreads));        

    m_cli11.add_option("-n, --min_range", m_args.minRange, "Minimum number for the PRNG range.")
        ->default_str(std::to_string(cli::minRange));

    m_cli11.add_option("-x, --max_range", m_args.maxRange, "Maximum number for the PRNG range.")
        ->default_str(std::to_string(cli::maxRange));

    m_cli11.add_option("-f, --file_name", m_args.fileName, "File Name for the export CSV.")
        ->default_str(cli::fileName);

    m_cli11.add_flag ("-c, --csv", m_args.exportCSV, "Export results to CSV");

}

bool CLIParser::cliParse(int argc, char** argv) {

    try {
        m_cli11.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        m_cli11.exit(e);
        return false;
    }
    return true;
}

} // namespace cli
