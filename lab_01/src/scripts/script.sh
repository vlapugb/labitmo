#!/bin/bash

# Переключаемся на ветку stg
git checkout stg

# Сливаем изменения из ветки dev в текущую ветку (stg)
git merge dev

# Устанавливаем метку времени (tag) для версии
version=$(date +'%Y%m%d%H%M%S')
git tag -a "v$version" -m "Release version $version"

# Записываем изменения
git push origin stg --tags

# Возвращаемся на ветку dev
git checkout dev
