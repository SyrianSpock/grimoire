#!/bin/bash

LIBRARY=$1
BRANCH=$2
BRANCH=${BRANCH:="master"}

set -eu

_GIT_SUBMODULE_SHA=$(git ls-tree master ${LIBRARY} | sed "s/\t/ /" | cut -d " " -f 3)
_GIT_REMOTE=$(GIT_DIR=${LIBRARY}/.git git remote get-url origin)

git rm -f ${LIBRARY}
git commit -m "Remove submodule ${LIBRARY}"

git remote add -f ${LIBRARY} ${_GIT_REMOTE}
git merge -s ours --no-commit --allow-unrelated-histories ${LIBRARY}/${BRANCH}
git read-tree --prefix=${LIBRARY}/ -u ${LIBRARY}/${BRANCH}
git commit -m "Subtree merged in ${LIBRARY}"

git remote rm ${LIBRARY}
