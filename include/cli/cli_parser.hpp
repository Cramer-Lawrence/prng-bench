#ifndef CLI_PARSER_HPP
#define CLI_PARSER_HPP

#include "cli_defaults.hpp"

#include <CLI/CLI.hpp>
#include <cstddef>
#include <string>

namespace cli {

struct Options {
    
    std::size_t     lowIteration   {cli::lowIteration};
    std::size_t     highIteration  {cli::highIteration};
    std::size_t     iterationSpread {cli::iterationSpread};
    std::size_t     numThreads      {cli::numThreads};
    uint64_t        minRange        {cli::minRange};
    uint64_t        maxRange        {cli::maxRange};
    std::string     fileName        {cli::fileName};
    bool            exportCSV       {cli::exportCSV};
};

class CLIParser {
private:
    CLI::App m_cli11;
    Options m_args {};

public:
    CLIParser();    

    bool cliParse(int argc, char** argv);
    const auto& getArgs() const noexcept {return m_args; }
};

} // namespace cli

#endif // CLI_PARSER_HPP
