/**
 * @file simulator.cpp
 * @author Trenton Ford
 * @date 28 Sep 2017
 * @brief Main simulation driver.* 
 *
 * Driver
 */

#include <boost/program_options.hpp>
#include <iostream>

namespace prog_ops = boost::program_options;

int main(int argc, char** argv)
{

	std::cout << "Entry" << std::endl;

	try
  	{
	    prog_ops::options_description desc{"Options"};
	    desc.add_options()
	      ("help,h", "Help")
	      ("s", "Cache Size")
	      ("a", "Associativity")
	      ("b", "Block Size")
	      ("p","Write Policy {op1,op2,etc}")
	      ("replacement", "Replacement Algorithm")
	      ("f", "<tracefile>");

	    prog_ops::variables_map vm;
	    prog_ops::store(prog_ops::parse_command_line(argc, argv, desc), vm);
	    prog_ops::notify(vm);

	    if (vm.count("help") || vm.count("h"))
	      std::cout << desc << '\n';
	    else if (vm.count("pi"))
	      std::cout << "Pi: " << "3.14" << '\n';
  	}
  catch (const prog_ops::error &ex)
  {
	    std::cerr << "&!&" << ex.what() << '\n';
	    return 0;
  }

}