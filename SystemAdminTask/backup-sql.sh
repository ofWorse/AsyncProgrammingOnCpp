#bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: $0 /path/to/config_file.config"
	exit 1
fi

source "$1"

if [ ! -d "$BACKUP_PATH" ]; then
	mkdir -p "$BACKUP_PATH"
fi

BACKUP_FILE="$BACKUP_PATH/$BACKUP_PREFIX.$(date +%Y.%m.%d_%H%M%S).tar.gz"
pg_dump -h "$DB_HOST" -U "DB_USER" -d "DB_BASE" -F t -f "$BACKUP_FILE"

if [ $? -ne 0 ]; then 
	echo "Backup execution error!"
	exit 1
fi


CURRENT_BACKUP_COUNT=$(ls -1 "$BACKUP_PATH/$BACKUP_PREFIX."* | wc -l)
while [ $CURRENT_BACKUP_COUNT -gt $BACKUP_COUNT ]; do
	OLDEST_BACKUP=$(ls -1 "$BACKUP_PATH/$BACKUP_PREFIX."* | sort | head -n 1)
	rm "$OLDEST_BACKUP"
	BACKUP_COUNT=$(ls -1 "$BACKUP_PATH/$BACKUP_PREFIX."* | wc -l)
done

LOG_FILE="$BACKUP_PATH/$BACKUP_PREFIX.$(date +%Y.%m.%d_%H%M%S).log"
{
	echo "Date&Time of backup execution startup: $(date +%Y-%m-%d\ %H:%M:%S)"
	echo "The database $DB_BASE is being backed up..."
	echo "File of backup copy: $BACKUP_FILE"
	echo "Number of backup copies: $BACKUP_COUNT"
	echo ""
} | tee "$LOG_FILE"

