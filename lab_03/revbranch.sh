#!/bin/bash

git checkout stg
git merge dev

git checkout prd 
git merge dev
