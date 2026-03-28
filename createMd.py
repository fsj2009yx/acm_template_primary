import os

# ===== 可配置 =====
ROOT_DIR = "."  # 仓库路径
OUTPUT_FILE = "acm_template.md"
IGNORE_DIRS = {".git", "__pycache__", ".idea", ".vscode","Codeforce"}
EXTENSIONS = {".cpp", ".cc", ".cxx"}  # 只处理这些文件


def is_code_file(filename):
    return any(filename.endswith(ext) for ext in EXTENSIONS)


def generate_markdown(root_dir):
    lines = []

    def dfs(path, depth):
        name = os.path.basename(path)

        # 目录标题
        if depth == 0:
            lines.append(f"# {name}\n\n")
        else:
            lines.append(f"{'#' * (depth + 1)} {name}\n\n")

        try:
            entries = sorted(os.listdir(path))
        except PermissionError:
            return

        # 先目录，后文件（更符合阅读习惯）
        entries.sort(key=lambda x: (
            not os.path.isdir(os.path.join(path, x)), x.lower()
        ))

        for entry in entries:
            if entry in IGNORE_DIRS:
                continue

            full_path = os.path.join(path, entry)

            if os.path.isdir(full_path):
                dfs(full_path, depth + 1)
            else:
                if is_code_file(entry):
                    file_title = f"{'#' * (depth + 2)} {entry}\n\n"
                    lines.append(file_title)

                    try:
                        with open(full_path, "r", encoding="utf-8") as f:
                            code = f.read()
                    except:
                        try:
                            with open(full_path, "r", encoding="gbk") as f:
                                code = f.read()
                        except:
                            code = "// 无法读取文件编码\n"

                    # 插入代码块
                    lines.append("```cpp\n")
                    lines.append(code.rstrip() + "\n")
                    lines.append("```\n\n")

    dfs(root_dir, 0)
    return lines


def main():
    md_lines = generate_markdown(ROOT_DIR)

    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        f.writelines(md_lines)

    print(f"生成完成: {OUTPUT_FILE}")


if __name__ == "__main__":
    main()