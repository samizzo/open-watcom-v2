#!/bin/sh
# *****************************************************************
# githubin.sh - initialize GitHub
# *****************************************************************
#
# 1. compress GitHub repository if necessary
# 2. update GitHub repository coverity_scan branch by master
#

echo_msg="githubin.sh - skipped"

if [ "$TRAVIS_BRANCH" = "master" ]; then
    if [ "$TRAVIS_EVENT_TYPE" = "push" ]; then
        #
        # configure Git client
        #
        git config --global user.email "travis@travis-ci.org"
        git config --global user.name "Travis CI"
        git config --global push.default simple
        #
        # clone GitHub repository
        #
        git clone $GITQUIET --branch=master https://${GITHUB_TOKEN}@github.com/${OWTRAVIS_SLUG}.git $OWTRAVIS_GITROOT
        #
        # compress GitHub repository to hold only a few last builds
        #
        cd $OWTRAVIS_GITROOT
        depth=`git rev-list HEAD --count`
        if [ $depth -gt 12 ]; then
            echo "githubin.sh - start compression"
            git checkout --orphan temp1
            git add -A
            git commit -am "Initial commit"
            git branch -D master
            git branch -m master
            git push -f origin master
            git branch --set-upstream-to=origin/master master
            echo "githubin.sh - end compression"
        fi
        cd $TRAVIS_BUILD_DIR
        echo_msg="githubin.sh - done"
    fi
elif [ "$COVERITY_SCAN_BRANCH" = 1 ]; then
    if [ "$TRAVIS_EVENT_TYPE" = "cron" ]; then
        #
        # configure Git client
        #
        git config --global user.email "travis@travis-ci.org"
        git config --global user.name "Travis CI"
        git config --global push.default simple
        #
        cd ..
        rm -rf $TRAVIS_BUILD_DIR
        git clone https://${GITHUB_TOKEN}@github.com/${TRAVIS_REPO_SLUG}.git $TRAVIS_BUILD_DIR
        cd $TRAVIS_BUILD_DIR
        #
        git checkout coverity_scan
        git merge master
        git add -A
        git commit -am "Travis CI update from master branch"
        git push -f origin coverity_scan
        #
        echo_msg="githubin.sh - done"
    fi
#else
fi

echo "$echo_msg"