require "rake/clean"
require "json"

PROJECT_NAME = "DungeonLoop"
ROOT_DIR = File.expand_path(File.dirname(__FILE__))
SRC_DIR = File.join(ROOT_DIR, "src")
BUILD_DIR = File.join(ROOT_DIR, "build")
DEPS_DIR = File.join(ROOT_DIR, "deps")
CUTE_DIR = File.join(DEPS_DIR, "cute")

SRC_FILES = FileList["#{SRC_DIR}/**/*.c"]
OBJ_FILES = SRC_FILES.pathmap("%{#{SRC_DIR},#{BUILD_DIR}}X.o")

CUTE_BRANCH = 'master'
INCLUDE_DIRS = [
  SRC_DIR,
  File.join(ROOT_DIR, "include"),
  File.join(CUTE_DIR, "include"),
  File.join(CUTE_DIR, "libraries"),
  File.join(CUTE_DIR, "libraries/cimgui")
]
CC = ENV.fetch('CC', '/usr/bin/clang')
CFLAGS = %w[
  -Wall
  -Wextra
  -Werror
  -g3
  -std=c17
]
TARGET = File.join(BUILD_DIR, PROJECT_NAME)
LIBS = %w[
  m
  pthread
  c++
  objc
]
COMPILE_COMMANDS_JSON = File.join(ROOT_DIR, "compile_commands.json")
APPLE_FRAMEWORKS = %w[
  AVFoundation
  AudioToolbox
  Cocoa
  Carbon
  CoreAudio
  CoreMedia
  CoreVideo
  CoreHaptics
  GameController
  UniformTypeIdentifiers
  ForceFeedback
  Foundation
  IOKit
  Metal
  MetalKit
  Network
  QuartzCore
]

directory BUILD_DIR
directory DEPS_DIR

CLEAN.include(OBJ_FILES)
CLEAN.include(TARGET)
CLOBBER.include(BUILD_DIR)

compile_commands = []

def source_for_object(obj_file)
  obj_file.pathmap("%{#{BUILD_DIR},#{SRC_DIR}}X.c")
end

rule '.o' => [->(f){source_for_object(f)}] do |t|
  mkdir_p File.dirname(t.name)
  cmd = [
    CC,
    *CFLAGS,
    *INCLUDE_DIRS.map { |dir| "-I#{dir}" },
    "-c",
    t.source,
    "-o",
    t.name,
  ]
  compile_commands << {
    directory: BUILD_DIR,
    arguments: cmd,
    file: t.source,
    output: t.name
  }
  sh cmd.join(' ')
end

file CUTE_DIR => DEPS_DIR do
  unless Dir.exist?(CUTE_DIR)
    sh "git clone https://github.com/RandyGaul/cute_framework.git --depth=1 --branch=#{CUTE_BRANCH} #{CUTE_DIR}"
  end

  cd CUTE_DIR do
    unless Dir.exist?(File.join(CUTE_DIR, "build"))
      cmake_flags = %w[
        CF_FRAMEWORK_BUILD_TESTS=OFF
        CF_FRAMEWORK_BUILD_SAMPLES=OFF
        CMAKE_EXPORT_COMPILE_COMMANDS=ON
      ].map { |flag| "-D#{flag}" }.join(' ')
      sh "cmake -G Ninja -B build #{cmake_flags}"
      sh "cmake --build build"
    end
  end
end

file TARGET => OBJ_FILES do
  static_libs = FileList["#{BUILD_DIR}/**/*.a"] + FileList["#{DEPS_DIR}/**/*.a"]
  cmd = [
    CC,
    *CFLAGS,
    *INCLUDE_DIRS.map { |dir| "-I#{dir}" },
    *LIBS.map { |lib| "-Xlinker -l#{lib}" },
    *APPLE_FRAMEWORKS.map { |framework| "-Xlinker -framework -Xlinker #{framework}" },
    *static_libs.map { "-Xlinker #{_1}" },
    *OBJ_FILES,
    "-o",
    TARGET,
  ]
  sh cmd.join(' ')
end

file COMPILE_COMMANDS_JSON => [TARGET] do
  puts "Writing compile_commands.json"
  File.write(COMPILE_COMMANDS_JSON, JSON.pretty_generate(compile_commands))
end

task compile: [BUILD_DIR, CUTE_DIR, TARGET, COMPILE_COMMANDS_JSON]
task run: :compile do
  sh TARGET
end

task default: :compile
