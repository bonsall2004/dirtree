#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <CLI/CLI.hpp>

namespace fs = std::filesystem;

bool should_ignore(const fs::path& path, const std::vector<fs::path>& ignore_list)
{
  for (const auto& ignore_path : ignore_list)
  {
    if (path == ignore_path)
    {
      return true;
    }
  }
  return false;
}

void print_directory_tree(const fs::path& path, const std::vector<fs::path>& ignore_list, const std::string& prefix = "", bool is_last = true, bool recursive = false, bool show_files = true, bool show_directories = true)
{
  if (!fs::exists(path) || !fs::is_directory(path) || should_ignore(path, ignore_list))
  {
    return;
  }

  std::cout << prefix;

  if (is_last)
  {
    std::cout << "`-- ";
  }
  else
  {
    std::cout << "|-- ";
  }

  std::cout << path.filename().string() << "/" << std::endl;

  std::vector<fs::path> entries;
  for (const auto& entry : fs::directory_iterator(path))
  {
    entries.push_back(entry.path());
  }

  for (size_t i = 0; i < entries.size(); ++i)
  {
    try
    {
      bool is_last_entry = (i == entries.size() - 1);
      auto& entry = entries[i];

      if (fs::is_directory(status(entry)))
      {
        if (show_directories)
        {
          std::cout << prefix + (is_last ? "    " : "|   ");
          if (is_last_entry)
          {
            std::cout << "`-- ";
          }
          else
          {
            std::cout << "|-- ";
          }
          std::cout << entry.filename().string() << "/" << std::endl;
        }
        if (recursive)
        {
          print_directory_tree(entry, ignore_list, prefix + (is_last ? "    " : "|   "), is_last_entry, recursive, show_files, show_directories);
        }
      }
      else if (show_files)
      {
        std::cout << prefix + (is_last ? "    " : "|   ");
        if (is_last_entry)
        {
          std::cout << "`-- ";
        }
        else
        {
          std::cout << "|-- ";
        }
        std::cout << entry.filename().string() << std::endl;
      }
    }
    catch (std::filesystem::filesystem_error& e)
    {
      continue;
    }
  }
}

int main(int argc, char* argv[])
{
  CLI::App app{ "Directory Tree Printer" };

  std::string root_path;
  std::vector<std::string> ignore_dirs;
  bool recursive = false;
  bool show_files = false;
  bool show_directories = false;

  app.add_option("path", root_path, "Root path of the directory tree")
    ->default_val(fs::current_path().string())
    ->check(CLI::ExistingDirectory);

  app.add_option("-i,--ignore", ignore_dirs, "Directories to ignore (relative to the root path)");
  app.add_flag("-r,--recursive", recursive, "Recursively scan directories");
  app.add_flag("-f,--files", show_files, "Only show files");
  app.add_flag("-d,--directories", show_directories, "Only show directories");

  CLI11_PARSE(app, argc, argv);

  if(recursive && !show_directories || show_files) show_files = true;

  std::vector<fs::path> ignore_list;
  for (const auto& dir : ignore_dirs)
  {
    ignore_list.push_back(fs::path(root_path) / dir);
  }

  if (!show_files && !show_directories)
  {
    show_directories = true;
  }

  print_directory_tree(root_path, ignore_list, "", true, recursive, show_files, show_directories);
  return 0;
}
