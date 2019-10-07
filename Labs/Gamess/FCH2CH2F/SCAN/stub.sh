for i in  $(cat angle); do
    ENERGY=$(grep 'IVIB=' $i.out | gawk '{print $8}')
    echo "$i $ENERGY" >> summary.dat
done

