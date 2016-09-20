local return_code="%(?..%{$fg[red]%}%? ↵%{$reset_color%})"

local user_host='%{$terminfo[bold]$fg[red]%}%n@%m:%{$reset_color%}'
local current_dir='%{$terminfo[bold]$fg[grey]%} %~%{$reset_color%}'
local git_branch='$(git_prompt_info)%{$reset_color%}'

PROMPT="%{$fg_bold[grey]%}╔[${user_host} ${current_dir}
%{$fg_bold[grey]%}╚${git_branch}%{$fg_bold[grey]%}%B>$%b "
RPS1="${return_code}"

ZSH_THEME_GIT_PROMPT_PREFIX="%{$fg_bold[grey]%}[%{$fg_bold[red]%}"
ZSH_THEME_GIT_PROMPT_SUFFIX="%{$fg_bold[grey]%}]%{$reset_color%}"

ZSH_THEME_GIT_PROMPT_CLEAN=" %{$fg_bold[green]✔%}"
ZSH_THEME_GIT_PROMPT_DIRTY=" %{$fg_bold[red]✗%}"

