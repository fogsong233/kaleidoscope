set_project("kaleidoscope")
set_version("1.0.0")
add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

set_toolchains("clang")

set_languages("c++23")

add_cxflags("-stdlib=libc++", "-Wno-c++20-compat", "-Wno-reserved-user-defined-literal",{force = true})

add_requires("gtest", {configs = {cxflags = "-stdlib=libc++"}, system=false })

if is_plat("macosx") then
    add_includedirs("/opt/homebrew/Cellar/llvm/20.1.8/include/c++/v1", {public = true})
    add_includedirs("/Library/Developer/CommandLineTools/SDKs/MacOSX26.0.sdk/usr/include/", {public = true})

    add_includedirs("/opt/homebrew/opt/llvm/include", {public = true})
    add_linkdirs("/opt/homebrew/opt/llvm/lib")
    add_links("llvm")

    add_ldflags("-lc++", "-lc++abi", {force = true})
    add_links("c++", "c++abi")
end

target("unitest")
    set_kind("binary")
    set_default(false)
    add_deps("frontend")
    add_packages("gtest")
    add_files("test/*.cpp")
    set_policy("build.c++.modules", true)

target("frontend")
    set_kind("shared")
    add_files("frontend/*.mpp", {public = true})
    add_files("frontend/*.cpp")
    set_policy("build.c++.modules", true)

target("main")
    set_kind("binary")
    add_files("src/*.cpp")
    add_deps("frontend")
    set_policy("build.c++.modules", true)

package("llvm")
    set_policy("package.install_locally", true)
    if has_config("llvm") then
        set_sourcedir(get_config("llvm"))
    else
        if has_config("release") then
            if is_plat("windows") then
                add_urls("https://github.com/clice-project/llvm-binary/releases/download/$(version)/x64-windows-msvc-release-lto.7z")
                add_versions("20.0.0", "c985d60825991eb6c7400be1b9872edf1de929908b12b282829efa52fda4c75c")
            elseif is_plat("linux") then
                add_urls("https://github.com/clice-project/llvm-binary/releases/download/$(version)/x86_64-linux-gnu-release-lto.tar.xz")
                add_versions("20.0.0", "adeb46c441265a4e442aea1b9d55f3950bc240aa84e2498b106d8dfd64e123cc")
            elseif is_plat("macosx") then
                add_urls("https://github.com/clice-project/llvm-binary/releases/download/20.1.5/arm64-macosx-apple-release-lto.tar.xz")
                add_versions("20.1.5", "f1c16076e0841b9e40cf21352d6661c7167bf6a76fa646b0fcba67e05bec2e7c")
            end
        else
            if is_plat("windows") then
                if is_mode("release") then
                    add_urls("https://github.com/clice-project/llvm-binary/releases/download/$(version)/x64-windows-msvc-release.7z")
                    add_versions("20.0.0", "4ef335845ebb52f8237bda3bcc7246b06085fdf5edc5cc6cf7f3a7c9ef655c09")
                end
            elseif is_plat("linux") then
                if is_mode("debug") then
                    add_urls("https://github.com/clice-project/llvm-binary/releases/download/$(version)/x86_64-linux-gnu-debug.tar.xz")
                    add_versions("20.0.0", "7dc045424a9667f20845dec058d211476b84300ebcfc8c3a3aabf41bff37cfd9")
                elseif is_mode("release") then
                    add_urls("https://github.com/clice-project/llvm-binary/releases/download/$(version)/x86_64-linux-gnu-release.tar.xz")
                    add_versions("20.0.0", "30ba7357eb40000f1d13d92242f7d87c3ff623e62205a41d10334d605739af89")
                end
            elseif is_plat("macosx") then
                if is_mode("debug") then
                    add_urls("https://github.com/clice-project/llvm-binary/releases/download/20.1.5/arm64-macosx-apple-debug.tar.xz")
                    add_versions("20.1.5", "743e926a47d702a89b9dbe2f3b905cfde5a06fb2b41035bd3451e8edb5330222")
                elseif is_mode("release") then
                    add_urls("https://github.com/clice-project/llvm-binary/releases/download/20.1.5/arm64-macosx-apple-release.tar.xz")
                    add_versions("20.1.5", "16f473e069d5d8225dc5f2cd513ae4a2161127385fd384d2a4737601d83030e7")
                end
            end
        end
    end

    if is_plat("linux", "macosx") then
        if is_mode("debug") then
            add_configs("shared", {description = "Build shared library.", default = true, type = "boolean", readonly = true})
        end
    end

    if is_plat("windows", "mingw") then
        add_syslinks("version", "ntdll")
    end

    on_install(function (package)
        if not package:config("shared") then
            package:add("defines", "CLANG_BUILD_STATIC")
        end

        os.vcp("bin", package:installdir())
        os.vcp("lib", package:installdir())
        os.vcp("include", package:installdir())
    end)

if has_config("release") then
    xpack("clice")
        if is_plat("windows") then
            set_formats("zip")
            set_extension(".7z")
        else
            set_formats("targz")
            set_extension(".tar.xz")
        end

        -- set_bindir(".")
        -- set_prefixdir("clice")

        -- add_targets("clice")
        -- add_installfiles(path.join(os.projectdir(), "docs/clice.toml"))

        -- on_load(function (package)
        --     local llvm_dir = package:target("clice"):dep("clice-core"):pkg("llvm"):installdir()
        --     package:add("installfiles", path.join(llvm_dir, "lib/clang/(**)"), {prefixdir = "lib/clang"})
        -- end)
end
