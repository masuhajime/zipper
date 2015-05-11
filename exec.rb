require 'fileutils'

def directories
  dir_project               = File.expand_path(File.dirname(__FILE__) + '/..')
  return [
  ]
end

def symlinks
  dir_project               = File.expand_path(File.dirname(__FILE__) + '/..')
  dir_project_class         = dir_project + '/Classes'
  return {
    dir_project+"/zipper/zipper" => dir_project_class + "/zipper",
  }
end

def create
  p "create"
  links = symlinks
  dirs = directories
  dirs.each{|dir|
    if !FileTest.exist?(dir)
      p "create directory #{dir}"
      FileUtils.mkdir_p(dir)
    end
  }

  links.each{|from, to|
    p "----------------------------------------------"
    p "#{from} => #{to}"
    if !File.exist?(to)
      if (0 == File.symlink(from, to))
        p "create success"
      else
        p "create failed"
      end
    else
      p "file exists"
    end
  }
end

def remove
  p "remove"
  links = symlinks
  links.each{|from, to|
    p "----------------------------------------------"
    p "#{to}"
    if File.symlink?(to)
      if (File.unlink(to))
        p "unlink success"
      else
        p "unlink failed"
      end
    else
      p "not exists"
    end
  }
end

def main(argv)
  cmd = nil
  if defined? argv[0]
    cmd = argv[0]
  end

  case cmd
  when "create"
    create
  when "remove"
    remove
  when "help"
    help
  else
    help
  end
end

def help
  print <<"EOS"
commands
  create    create symlinks
  remote    remove symlinks
  help      this
EOS
end

main(ARGV)
