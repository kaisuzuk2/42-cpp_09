#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

#最大66回
MAX_COMPARISONS=66

#21要素
ELEMENT_COUNT=21

TEST_RUNS=100

echo "=== PmergeMe 比較回数チェック (${ELEMENT_COUNT}個の要素) ==="
echo "最大許容回数: ${MAX_COMPARISONS}回"
echo ""

# ランダムな21個の数字を生成してテスト
for i in $(seq 1 $TEST_RUNS); do
    # numbers=$(shuf -i 1-$ELEMENT_COUNT -n $ELEMENT_COUNT |  tr '\n' ' ')
    numbers=$(jot -r $ELEMENT_COUNT 1 100000 | sort -u | tr '\n' ' ')
    echo "テスト #$i:"
    echo "入力: $numbers"

    output=$(./PmergeMe $numbers 2>&1)

    # 比較回数を抽出（"Count : 123" の形式）
    # comparisons=$(echo "$output" | grep -oP 'Count\s*:\s*\K\d+')
    comparisons=$(echo "$output" | grep -oE 'Count[[:space:]]*:[[:space:]]*[0-9]+' | grep -oE '[0-9]+')
    echo "comparisons=$comparisons, $MAX_COMPARISONS"
    if [ -z "$comparisons" ]; then
        echo -e "${YELLOW}警告: 比較回数を抽出できませんでした${NC}"
        echo "出力: $output"
    else
        if [ "$comparisons" -le "$MAX_COMPARISONS" ]; then
            echo -e "${GREEN}✓ 比較回数: ${comparisons}回 (OK)${NC}"
        else
            echo -e "${RED}✗ 比較回数: ${comparisons}回 (最大${MAX_COMPARISONS}回を超過!)${NC}"
            exit 1
        fi
    fi
    echo ""
done

echo "=== 特定のテストケース ==="
# 昇順ソート済み
echo "テスト: 昇順ソート済み"
sorted_asc=$(seq 1 $ELEMENT_COUNT | tr '\n' ' ')
./PmergeMe $sorted_asc
echo ""

# 降順ソート済み
echo "テスト: 降順ソート済み"
sorted_desc=$(seq $ELEMENT_COUNT -1 1 | tr '\n' ' ')
./PmergeMe $sorted_desc
echo ""