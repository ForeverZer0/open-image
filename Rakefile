require 'bundler/gem_tasks'
require 'rake/testtask'

require 'rake/extensiontask'

task :build => :compile

Rake::ExtensionTask.new('open_image') do |ext|
  ext.lib_dir = 'lib/open_image'
end

task :default => [:clobber, :compile]

task :doc do
  `yardoc`
  `yard server --reload`
end
