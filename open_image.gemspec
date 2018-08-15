
lib = File.expand_path('lib', __dir__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'open_image/version'

Gem::Specification.new do |spec|
  spec.name          = 'open_image'
  spec.version       = OpenImage::VERSION
  spec.authors       = ['Eric Freed']
  spec.email         = ['efreed09@gmail.com']

  spec.summary       = %q{Cross-platform and dependency-free image library with emphasis on performance and ease-of-use.}
  spec.description   = %q{Currently Under Construction}
  spec.homepage      = "https://github.com/ForeverZer0/open-image"
  spec.license       = 'MIT'

  spec.files         = Dir.chdir(File.expand_path('..', __FILE__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  end

  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
  spec.extensions    = ['ext/open_image/extconf.rb']

  spec.required_ruby_version = '>= 2.0.0'

  spec.add_development_dependency 'bundler', '~> 1.16'
  spec.add_development_dependency 'rake', '~> 10.0'
  spec.add_development_dependency 'rake-compiler', '~> 1.0'
end
