else if (cmd == "new" && argc == 3) {
    std::string projName = argv[2];
    std::string cmd = "cp -r templates/default_project " + projName;
    system(cmd.c_str());
    std::cout << "Created new Windstrom project: " << projName << "\n";
}
