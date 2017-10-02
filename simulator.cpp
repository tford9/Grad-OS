/**
 * @file simulator.cpp
 * @author Trenton Ford
 * @date 28 Sep 2017
 * @brief Main simulation driver.* 
 *
 * Driver
 */

#include <iostream>
#include <vector>
#include <string> 

#include <boost/program_options.hpp>

// #include "utilities.hpp"

namespace prog_ops = boost::program_options;

int main(int argc, char *argv[])
{
	int associativity;
	int num_of_blocks;
	int cache_size;
	int block_size;
	int wp;
	int rp; 

    prog_ops::options_description desc{"Options"};
    desc.add_options()
	    ("help,h", "Help")
	    ("a"     , "Associativity")
	    ("f"     , prog_ops::value<int>(), "<tracefile>")
	    ("cs"    , prog_ops::value<int>(&cache_size)->default_value(1), "Cache Size")
	    ("bs"    , prog_ops::value<int>(&block_size)->default_value(1), "Block Size")
	    ("wp"    , prog_ops::value<int>(&wp)->default_value(1), "Write Policy {Write-Through = 1, Write-Back = 2}")
	    ("rp"    , prog_ops::value<int>(&rp)->default_value(1), "Replacement Policy {LRU = 1, FIFO = 2 ,etc}")
  	;

    prog_ops::variables_map options_map;

	// This should be removed from the main
	try
  	{
	    prog_ops::store(prog_ops::parse_command_line(argc, argv, desc), options_map);
	    prog_ops::notify(options_map);

	    if (options_map.count("help") || options_map.count("h"))
	    {
	      	std::cout << desc << '\n';
	      	return 1;
	    }
	  	else if (options_map.count("a"))
  		{
  			// placeholder @TF
	    }
	    else if (options_map.count("cs"))
	    {
	      	std::cout << "Cache Size set to: " << cache_size << '\n';
      	}
	  	else if (options_map.count("bs"))
  		{
	      	std::cout << "Block Size set to: " << block_size << '\n';
	    }
	  	else if (options_map.count("wp"))
  		{
	      	std::cout << "Write Policy set to: " << wp << '\n';
	    }
	  	else if (options_map.count("rp"))
  		{
	      	std::cout << "Replacement Policy set to: " << rp << '\n';
	    }
	  	else if (options_map.count("f"))
  		{
  			// placeholder @TF
	    }
  	}
	catch (const prog_ops::error &ex)
	{
	    std::cerr << "&!&" << ex.what() << '\n';
	    return 1;
	}

	num_of_blocks = cache_size/block_size;

	return 0;

}